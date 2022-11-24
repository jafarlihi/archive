<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$teacherid = $_GET['id'];
$teacherusername = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `id` = '$teacherid'"), 0, 'username');
echo '<h1>Change email address of instructor account: ', $teacherusername, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>New email address:<br>
		<input type="text" name="newemail">
		</li>
		<li>
		<input type="submit" value="Change Email Address">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$newemail = $_POST['newemail'];
	mysql_query("UPDATE `logins` SET email='$newemail' WHERE `id` = '$teacherid';");
	echo 'Email address was updated successfully.';
	}
?>

<?php include '../includes/overall/footer.php';?>