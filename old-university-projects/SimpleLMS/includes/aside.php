<aside>
<?php
if (logged_in() === true) {
    include 'widgets/loggedin.php';
} else {
    include 'widgets/login.php';
}

if ($user_data['access'] == '0') {
    include 'widgets/classes.php';
}

if ($user_data['access'] == '1') {
    include 'widgets/teacherwidget.php';
}

if ($user_data['access'] == '2') {
    include 'widgets/adminwidget.php';
}
?>
</aside>
