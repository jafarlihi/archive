<?php include '../core/init.php';?>
<?php 
protect_page(); 
protect_page_admin();
?>
<?php include '../includes/overall/header.php';?>

<h1>Manage Classes</h1>
<br>
<a class="myButton" href="registerclass.php">Register a New Class</a><br><br>
<br>
<br>
Edit an existing class:&nbsp;
<form action="" method="post" style="display:inline;">
<select name="class" style="min-width: 150px;">
<option disabled="disabled">Pick a class</option>
<?php
	$result = mysql_query("SELECT COUNT(1) FROM `classes`");
	$num_rows = mysql_result($result, 0, 0);
	$i = 0;
	$classes = array();
	while ($i < $num_rows){
	$classes[$i] = mysql_result(mysql_query("SELECT `name` FROM `classes`"), $i, 'name');
	$i++;
	}
	while ($i > 0){
        echo "<option value='".$classes[$i-1]."'>".$classes[$i-1]."</option>";
	$i--;
	}
?>
<input type="submit" value="Edit">
</select>
</form>

<?php
if (empty($_POST) === false){
$_SESSION['editclass_name'] = $_POST['class'];
header('Location: admineditclass.php');
}
?>

<?php include '../includes/overall/footer.php';?>