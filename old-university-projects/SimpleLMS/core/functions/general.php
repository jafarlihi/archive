<?php

if (!function_exists('logged_in_redirect')) {
    function logged_in_redirect()
    {
        if (logged_in() === true) {
            header('Location: ../../index.php');
            exit();
        }
    }
}

if (!function_exists('protect_page')) {
    function protect_page()
    {
        if (logged_in() === false) {
            header('Location: ../../protected.php');
            exit();
        }
    }
}

if (!function_exists('protect_page_admin')) {
    function protect_page_admin()
    {
        $user_id = $_SESSION['id'];
        $user_access = mysql_result(mysql_query("SELECT `access` FROM `logins` WHERE `id` = '$user_id'"), 0, 'access');
        if ($user_access !== '2') {
            header('Location: ../../protected.php');
            exit();
        }
    }
}

if (!function_exists('protect_page_teacher')) {
    function protect_page_teacher()
    {
        $user_id = $_SESSION['id'];
        $user_access = mysql_result(mysql_query("SELECT `access` FROM `logins` WHERE `id` = '$user_id'"), 0, 'access');
        if ($user_access == '0') {
            header('Location: ../../protected.php');
            exit();
        }
    }
}

if (!function_exists('sanitize')) {
    function sanitize($data)
    {
        return mysql_real_escape_string($data);
    }
}

if (!function_exists('array_sanitize')) {
    function array_sanitize(&$item)
    {
        $item = mysql_real_escape_string($item);
    }
}

if (!function_exists('output_errors')) {
    function output_errors($errors)
    {
        return sprintf(
            '<ul><li><font color="red">%s</font></li></ul>',
            implode('</li></font><li><font color="red">', $errors)
        );
    }
}
