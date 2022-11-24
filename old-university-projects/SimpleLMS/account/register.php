<?php include '../core/init.php';?>
<?php logged_in_redirect();?>
<?php include '../includes/overall/header.php';?>

<?php
if (empty($_POST) === false){
	foreach($_POST as $key=>$value){
		if(empty($value)){
			$errors[] = 'Please fill in all of the fields.';
			break 1;
		}
	}
	
if (empty($errors) === true){
	if (user_exists($_POST['username']) === true){
		$errors[] = 'Sorry, the username \'' . $_POST['username'] . '\' is already taken.';
	}
	if (preg_match("/\\s/", $_POST['username']) == true){
		$errors[] = 'Username must not contain any spaces.';
	}
	if (strlen($_POST['password']) < 6){
		$errors[] = 'Password must be at least 6 characters.';
	}
	if ($_POST['password'] !== $_POST['password2']){
		$errors[] = 'Passwords do not match.';
	}
	if (filter_var($_POST['email'], FILTER_VALIDATE_EMAIL) === false){
		$errors[] = 'A valid email address is required.';
	}
	if (email_exists($_POST['email']) === true){
		$errors[] = 'Sorry, the email \'' . $_POST['email'] . '\' is already in use.';
	}
        if (phone_exists($_POST['phone']) === true){
		$errors[] = 'Sorry, the phone number \'' . $_POST['phone'] . '\' is already in use.';
	}
	if (is_phone_number($_POST['phone']) === false){
		$errors[] = 'Please enter a valid phone number.';
	}
}
}
?>

<h1>Register</h1>

<?php
if (isset($_GET['success']) && empty($_GET['success'])){
	echo 'Registration is successful. You can login now.';
} else {
if (empty($_POST) === false && empty($errors) === true){
	$register_data = array(
		'username' => $_POST['username'],
		'password' => $_POST['password'],
		'name' => $_POST['name'],
		'surname' => $_POST['surname'],
		'email' => $_POST['email'],
		'phone' => $_POST['phone']
	);
	register_user($register_data);
	header('Location: register.php?success');
	exit();
} else if (empty($errors) === false) {
	echo output_errors($errors);
}
?>


<form action="" method="post">
	<ul>
		<li>
			Username:<br>
			<input type="text" name="username">
		</li>
		<li>
			Password:<br>
			<input type="password" name="password">
		</li>
		<li>
			Re-enter password:<br>
			<input type="password" name="password2">
		</li>
		<li>
			First name:<br>
			<input type="text" name="name">
		</li>	
		<li>
			Last name:<br>
			<input type="text" name="surname">
		</li>
		<li>
			Email:<br>
			<input type="text" name="email">
		</li>
		<li>
			Phone:<br>
			<input type="text" name="phone">
		</li>
		<li>
			<input type="submit" value="Register">
		</li>
	</ul>
</form>

<?php 
}
include '../includes/overall/footer.php'; 
?>