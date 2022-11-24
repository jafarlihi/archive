<?php include '../core/init.php';?>
<?php 
protect_page(); 
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$teacherusername = $_SESSION['editteacher_username'];
unset($_SESSION['editteacher_username']);
$teacherid = mysql_result(mysql_query("SELECT `id` FROM `logins` WHERE `username` = '$teacherusername'"), 0, 'id');
?>

<h1>Editing instructor account with the username of: <?php echo $teacherusername; ?></h1>

<p>
<br><br>
<a class="myButton" href="changeteacherusername.php?id=<?php echo "$teacherid";?>" >Change Username</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" href="changeteacherphone.php?id=<?php echo "$teacherid";?>" >Change Phone Number</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" href="changeteacheremail.php?id=<?php echo "$teacherid";?>" >Change Email Address</a>&nbsp; &nbsp; &nbsp; <br> <br> <br>
</p>

<?php include '../includes/overall/footer.php';?>