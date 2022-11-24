<?php
ob_start();
session_start();
require 'database/connect.php';
require 'functions/users.php';
require 'functions/general.php';

date_default_timezone_set("Asia/Baku");

if (logged_in() === true) {
    $session_user_id = $_SESSION['id'];
    $user_data = user_data(
        $session_user_id,
        'id',
        'username',
        'password',
        'access',
        'name',
        'surname',
        'email',
        'phone'
    );
}
