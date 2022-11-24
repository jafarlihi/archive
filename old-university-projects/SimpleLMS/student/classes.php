<?php include '../core/init.php';?>
<?php protect_page(); ?>
<?php include '../includes/overall/header.php';?>

<h1>
<?php
        $classid = $_GET['id'];
        $classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
        echo $classname;
?>
</h1>

<b>Class ID:</b>
<?php echo $classid;?>
<br>
<br>
<p>
<b>Instructor information:</b>
<?php
$teacherid = mysql_result(mysql_query("SELECT `teacherid` FROM `classes` WHERE `id` = '$classid'"), 0, 'teacherid');
$teacherusername = mysql_result(mysql_query("SELECT `username` FROM `logins` WHERE '$teacherid' = `id`"), 0, 'username');
$teachername = mysql_result(mysql_query("SELECT `name` FROM `logins` WHERE '$teacherid' = `id`"), 0, 'name');
$teachersurname = mysql_result(mysql_query("SELECT `surname` FROM `logins` WHERE '$teacherid' = `id`"), 0, 'surname');
$teacheremail = mysql_result(mysql_query("SELECT `email` FROM `logins` WHERE '$teacherid' = `id`"), 0, 'email');
$teacherphone = mysql_result(mysql_query("SELECT `phone` FROM `logins` WHERE '$teacherid' = `id`"), 0, 'phone');

sprintf(
    '<br /> %s %s <br /> Email: %s <br /> Phone: %s <br /> Username: %s',
    $teachername,
    $teachersurname,
    $teacheremail,
    $teacherphone,
    $teacherusername
);
?>
<br>
<br>
<br>
<b>Options:</b>
<br>
<br>
<br>
<a href="classinfo.php?id=<?php echo "$classid";?>" ><img src="../assets/images/buttons/classinfo.png"></a>
<a href="viewgrades.php?id=<?php echo "$classid";?>" ><img src="../assets/images/buttons/viewgrades.png"></a>
<a href="viewfiles.php?id=<?php echo "$classid";?>" ><img src="../assets/images/buttons/viewfiles.png"></a>
<a href="../forums/board.php?id=<?php echo "$classid";?>" ><img src="../assets/images/buttons/messageboard.png"></a>
<a><img src="../assets/images/buttons/notifications.png"></a>
<a><img src="../assets/images/buttons/homework.png"></a>
</p>

<?php include '../includes/overall/footer.php';?>
