<?php
class PPSDK
{
    private static $api_clientId = ''; // PayPal API ClientID.
    private static $api_clientSecret = ''; // PayPal API ClientSecret.

    // Makes a single payout. Takes in customer's PayPal email address, requested amount (E.g. '45.75'), and the requested currency (E.g. 'USD', 'AZN', etc.) as arguments.
    public static function sendPayment ($receiver_email, $amount, $currency)
    {
        require __DIR__  . '/../vendor/autoload.php'; // Requires Paypal's REST API SDK for PHP.

        $amount = number_format((float) $amount, 2, '.', ''); // Changes float precision to 2 decimals points to be able to adhere to PayPal API standards.

        $apiContext = new \PayPal\Rest\ApiContext(
            new \PayPal\Auth\OAuthTokenCredential(
                self::$api_clientId,
                self::$api_clientSecret
            )
        );

        $payouts = new \PayPal\Api\Payout();
        $senderBatchHeader = new \PayPal\Api\PayoutSenderBatchHeader();

        $senderBatchHeader->setSenderBatchId(uniqid())
            ->setEmailSubject(""); // Replace with desired email title.

        $senderItem = new \PayPal\Api\PayoutItem();
        $senderItem->setRecipientType('Email')
            ->setNote('') // Replace with desired email body.
            ->setReceiver($receiver_email) // Receiver's email address.
            ->setAmount(new \PayPal\Api\Currency('{ 
                "value":"' . $amount . '",
                "currency":"' . $currency . '"
            }')); // Value is amount sent, currency specifies the type of currency requested. Refer to https://developer.paypal.com/docs/integration/direct/rest-api-payment-country-currency-support/ for list of supported currency types. Do note that additional fee is charged from the vendor along with the specified amount. Check PayPal's website for fees and notify users that additional fee will be charged from their account balance.

        $payouts->setSenderBatchHeader($senderBatchHeader)
            ->addItem($senderItem);

        $request = clone $payouts;

        try {
            $output = $payouts->createSynchronous($apiContext);
        } catch (Exception $ex) {
            exit(1);
        }

        return $output; // Returns PayPal's response. 
    }
}
