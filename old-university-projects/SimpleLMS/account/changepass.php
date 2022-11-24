<?php include '../core/init.php';?>
<?php protect_page();?>

<?php
if (empty($_POST) === false){
	$required_fields = array('current_password', 'password', 'password_again');
		foreach($_POST as $key=>$value){
		if(empty($value)){
			$errors[] = 'Please fill in all of the fields.';
			break 1;
		}
	}
	
	if($_POST['current_password'] === $user_data['password']){
		if ($_POST['password'] !== $_POST['password_again']){
			$errors[] = 'New passwords do not match.';
		} else if (strlen($_POST['password']) < 6) {
			$errors = 'New password should be longer than 6 characters.';
		}
		
	} else {
		$errors[] = 'Current password is incorrect.';
	}
	}
?>

<?php include '../includes/overall/header.php';?>

<h1>Change Password</h1>

<?php
if (isset($_GET['success']) && empty($_GET['success'])){
	echo 'Password was succesfully changed.';
} else {
if (empty($_POST) === false && empty($errors) === true){
	change_password($session_user_id, $_POST['password']);
	header('Location: changepass.php?success');
} else if (empty($errors) === false) {
	echo output_errors($errors);
}
?>

<form action="" method="post">
	<ul>
		<li>Current password:<br>
		<input type="password" name="current_password">
		</li>
		<li>New password:<br>
		<input type="password" name="password">
		</li>
		<li>New password again:<br>
		<input type="password" name="password_again">
		</li>
                <br>
		<li>
		<input type="submit" value="Change Password">
		</li>
	</ul>
</form>

<?php
} 
include '../includes/overall/footer.php';
?>