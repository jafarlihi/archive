<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$teacherid = $_GET['id'];
$teacherusername = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE `id` = '$teacherid'"), 0, 'username');
echo '<h1>Change phone number of the instructor account: ', $teacherusername, '</h1>';
?>

<form action="" method="post">
	<ul>
		<li>New phone number:<br>
		<input type="text" name="newnumber">
		</li>
		<li>
		<input type="submit" value="Change Phone Number">
		</li>
	</ul>
</form>

<?php
	if (empty($_POST) === false){
	$newnumber = $_POST['newnumber'];
	mysql_query("UPDATE `logins` SET phone='$newnumber' WHERE `id` = '$teacherid';");
	echo 'Phone number was updated successfully..';
	}
?>

<?php include '../includes/overall/footer.php';?>