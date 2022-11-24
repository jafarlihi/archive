<?php
class PPNoSDK
{
    private static $api_clientId = ''; // PayPal API ClientID.
    private static $api_clientSecret = ''; // PayPal API ClientSecret.

    // Requests and returns OAuth 2.0 access token from PayPal.
    private static function getAccessToken()
    {
        $curl = curl_init(); // Initializes cURL instance.

        // cURL options.
        curl_setopt($curl, CURLOPT_URL, "https://api.sandbox.paypal.com/v1/oauth2/token");
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($curl, CURLOPT_HTTPHEADER, array("Accept: application/json", "Accept-Language: en_US"));
        curl_setopt($curl, CURLOPT_USERPWD, self::$api_clientId . ":" . self::$api_clientSecret);
        curl_setopt($curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");

        $response = curl_exec($curl);
        curl_close($curl);

        $response = json_decode($response, true);
        return $response['access_token']; // Returns access token from received response.
    }

    // Makes a single payout.
    public static function sendPayment ($receiver_email, $amount, $currency)
    {
        $amount = number_format((float) $amount, 2, '.', ''); // Changes float precision to 2 decimals points to be able to adhere to PayPal API standards.

        $email_subject = ''; // Change PayPal email title to the desired text.
        $email_note = ''; // Change to desired note to add to the PayPal email.

        $curl_data = '{
            "sender_batch_header":{
                "email_subject":"' . $email_subject . '",
                "recipient_type":"EMAIL"
            },
            "items":[
                {
                    "recipient_type":"EMAIL",
                    "amount":{
                        "value":"' . $amount . '",
                        "currency":"' . $currency . '"
                    },
                    "note":"' . $email_note . '",
                    "receiver":"' . $receiver_email . '"
                }
            ]
        }';

        $curl = curl_init(); // Initializes cURL instance.

        // cURL options.
        curl_setopt($curl, CURLOPT_URL, "https://api.sandbox.paypal.com/v1/payments/payouts?sync_mode=true");
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($curl, CURLOPT_HTTPHEADER, array("Content-Type:application/json", "Authorization: Bearer " . self::getAccessToken()));
        curl_setopt($curl, CURLOPT_POSTFIELDS, $curl_data);

        $response = curl_exec($curl);
        curl_close($curl);

        $response = json_decode($response, true);
        return $response;
    }
}
