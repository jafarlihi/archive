<?php

if (!function_exists('change_password')) {
    function change_password($user_id, $password)
    {
        $user_id = (int) $user_id;
        mysql_query("UPDATE `logins` SET `password` = '$password' WHERE `id` = '$user_id'");
    }
}

if (!function_exists('register_user')) {
    function register_user($register_data)
    {
        array_walk($register_data, 'array_sanitize');
        $fields = '`' . implode('`, `', array_keys($register_data)) . '`';
        $data = '\'' . implode('\', \'', $register_data) . '\'';
        mysql_query("INSERT INTO `logins` ($fields) VALUES ($data)");
    }
}

if (!function_exists('user_data')) {
    function user_data($id)
    {
        $data = array();
        $id   = (int) $id;

        $func_num_args = func_num_args();
        $func_get_args = func_get_args();

        if ($func_num_args > 1) {
            unset($func_get_args[0]);
            $fields = '`' . implode('`, `', $func_get_args) . '`';
            $data = mysql_fetch_assoc(mysql_query("SELECT $fields FROM `logins` WHERE `id` = $id"));
            return $data;
        }
    }
}

if (!function_exists('logged_in')) {
    function logged_in()
    {
        return isset($_SESSION['id']);
    }
}

if (!function_exists('user_exists')) {
    function user_exists($username)
    {
        $username = sanitize($username);
        return (mysql_result(mysql_query(
            sprintf(
                "SELECT COUNT(`id`) FROM `logins` WHERE `username` = '%s'",
                $username
            )
        ), 0) == 1) ? true : false;
    }
}

if (!function_exists('email_exists')) {
    function email_exists($email)
    {
        $email = sanitize($email);

        return (mysql_result(mysql_query(
            sprintf(
                "SELECT COUNT(`id`) FROM `logins` WHERE `email` = '%s'",
                $email
            )
        ), 0) == 1) ? true : false;
    }
}

if (!function_exists('phone_exists')) {
    function phone_exists($phone)
    {
        $phone = sanitize($phone);

        return (mysql_result(mysql_query(
            sprintf(
                "SELECT COUNT(`id`) FROM `logins` WHERE `phone` = '%s'",
                $phone
            )
        ), 0) == 1) ? true : false;
    }
}

if (!function_exists('is_phone_number')) {
    function is_phone_number($phone)
    {
        $num_length = strlen((string) $phone);

        return (is_numeric($phone) && $num_length > 7 && $num_length < 25);
    }
}

if (!function_exists('id_from_username')) {
    function id_from_username($username)
    {
        $username = sanitize($username);

        return mysql_result(mysql_query(
            sprintf(
                "SELECT (`id`) FROM `logins` WHERE `username` = '%s'",
                $username
            )
        ), 0, 'id');
    }
}

if (!function_exists('username_from_id')) {
    function username_from_id($id)
    {
        $id = (int) sanitize($id);

        return mysql_result(mysql_query(
            sprintf(
                "SELECT (`username`) FROM `logins` WHERE `id` = '%d'",
                $id
            )
        ), 0, 'username');
    }
}

if (!function_exists('email_from_username')) {
    function email_from_username($username)
    {
        $username = sanitize($username);

        return mysql_result(mysql_query(
            sprintf(
                "SELECT (`email`) FROM `logins` WHERE `username` = '%s'",
                $username
            )
        ), 0, 'email');
    }
}

if (!function_exists('login')) {
    function login($username, $password)
    {
        $id       = id_from_username($username);
        $username = sanitize($username);
        $password = sanitize($password);

        return (
            @mysql_result(mysql_query(
                sprintf(
                    "SELECT (`id`) FROM `logins` WHERE `username` = '%s' AND `password` = '%s'",
                    $username,
                    $password
                )
            ), 0) == true)
            ? $id
            : false;
    }
}
