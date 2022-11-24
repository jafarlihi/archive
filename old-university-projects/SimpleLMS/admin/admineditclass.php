<?php include '../core/init.php';?>
<?php 
protect_page(); 
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classname = $_SESSION['editclass_name'];
unset($_SESSION['editclass_name']);
$classid = mysql_result(mysql_query("SELECT `id` FROM `classes` WHERE '$classname' = `name`"), 0, 'id');
?>

<h1>Editing class: <?php echo $classname; ?></h1>

<p>
<br>
<a class="myButton" style="display: inline-block; width: 113px;" href="changeclassname.php?id=<?php echo "$classid";?>" >Change Name</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 113px;" href="changeclassinfo.php?id=<?php echo "$classid";?>" >Change Info</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 113px;" href="changeclassteacher.php?id=<?php echo "$classid";?>" >Change Instructor</a>&nbsp; &nbsp; &nbsp; <br> <br> <br>
<a class="myButton" style="display: inline-block; width: 113px;" href="addstudentclass.php?id=<?php echo "$classid";?>" >Add Student</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 113px;" href="removestudentclass.php?id=<?php echo "$classid";?>" >Remove Student</a>&nbsp; &nbsp; &nbsp;
<a class="myButton" style="display: inline-block; width: 113px;" href="deleteclass.php?id=<?php echo "$classid";?>" >Delete Class</a>&nbsp; &nbsp; &nbsp; <br> <br> <br>
<a class="myButton" style="display: inline-block; width: 113px;" href="../forums/board.php?id=<?php echo "$classid";?>" >Message Board</a>&nbsp; &nbsp; &nbsp;
</p>

<?php include '../includes/overall/footer.php';?>