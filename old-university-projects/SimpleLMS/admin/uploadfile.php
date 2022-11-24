<?php include '../core/init.php';?>
<?php 
protect_page();
protect_page_teacher();
?>
<?php include '../includes/overall/header.php';?>

<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo '<h1>Upload a file for the class named ', $classname, ':</h1>';
?>

<html>
<body>
<form action="" method="post" enctype="multipart/form-data">
<label for="file">Choose a file:</label>
<input type="file" name="file" id="file"><br><br>
<input type="submit" name="submit" value="Upload">
</form>
</body>
</html>

<?php
        if (empty($_FILES) === false){
        $not_allowed = array('php', 'html', 'htm', 'htaccess', 'php3', 'phtml', 'phtm', 'css', 'xml', 'asp');
        $filename = $_FILES['file']['name'];
        $extension = pathinfo($filename, PATHINFO_EXTENSION);
	if(in_array($extension, $not_allowed)){
        echo 'Uploaded file\'s extension is not allowed.';
        }
        }
        if (empty($_FILES) === false and !in_array($extension, $not_allowed)){
	$url = "../upload/classes/" . $classid;
	if (!file_exists($url)){
        mkdir($url, 0777, true);
        }
        move_uploaded_file($_FILES["file"]["tmp_name"], $url . "/" . $_FILES["file"]["name"]);
	echo "File uploaded successfully.";
}
?>

<?php include '../includes/overall/footer.php';?>
