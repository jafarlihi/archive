<?php include '../core/init.php';?>
<?php logged_in_redirect();?>
<?php include '../includes/overall/header.php';?>

<?php
if (empty($_POST) === false) {
	$username = $_POST['username'];
	$password = $_POST['password'];
	if (empty($username) === true || empty($password) === true){
		$errors[] = 'Username and password fields cannot be left blank.';
	} else if (user_exists($username) === false){
		$errors[] = 'This username is not registered.';
	} else {
	$login = login($username, $password);
	if ($login === false){
	$errors[]= 'Username/password combination is incorrect.';
	} else {
		$_SESSION['id'] = $login;
		header('Location: ../index.php');
		exit();
	}
	}
	echo output_errors($errors);
}
?>

<?php include '../includes/overall/footer.php';?>