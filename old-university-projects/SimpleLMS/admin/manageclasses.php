<?php include '../core/init.php';?>
<?php 
protect_page(); 
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
?>

<h1>Editing the class named <?php echo $classname;?></h1>
<p>
<br><br>
<a class="myButton" style="display: inline-block; width: 135px;" href="changeclassinfo.php?id=<?php echo "$classid";?>" >Change Class Info</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 135px;" href="addstudentclass.php?id=<?php echo "$classid";?>" >Add Students</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 135px;" href="removestudentclass.php?id=<?php echo "$classid";?>" >Remove Students</a>&nbsp; &nbsp; &nbsp; <br> <br> <br>
<a class="myButton" style="display: inline-block; width: 135px;" href="uploadfile.php?id=<?php echo "$classid";?>" >Upload File</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 135px;" href="managegrades.php?id=<?php echo "$classid";?>" >Manage Grades</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 135px;" href="../forums/board.php?id=<?php echo "$classid";?>" >Message Board</a>&nbsp; &nbsp; &nbsp; <br><br><br>
<a class="myButton" style="display: inline-block; width: 135px;">Manage Homeworks</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 135px;">Manage Notifications</a>&nbsp; &nbsp; &nbsp;  
</p>

<?php include '../includes/overall/footer.php';?>
