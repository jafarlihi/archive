<?php include 'core/init.php';?>
<?php include 'includes/overall/header.php';?>

<?php
if (logged_in() === true) {
    if ($user_data['access'] == '0') {
        echo "<h1>You are logged in as Student. Please select a class to continue.</h1>";
        echo "<p>No class is selected.</p>";
    } elseif ($user_data['access'] == '1') {
        echo "<h1>You are logged in as Instructor.</h1>";
        echo "<p>Please select an option from sidebar to continue.</p>";
    } elseif ($user_data['access'] == '2') {
        echo "<h1>You are logged in as Admin.</h1>";
        echo "<p>Please select an option from sidebar to continue.</p>";
    }
} else {
    echo "<h1>You are not logged in.</h1>";
    echo "<p>Homepage content goes here.<br></p>";
}
?>

<?php include 'includes/overall/footer.php';?>
