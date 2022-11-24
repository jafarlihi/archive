<?php include '../core/init.php';?>
<?php protect_page();?>
<?php include '../includes/overall/header.php';?>

<h1>
<?php
$classid = $_GET['id'];
$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
echo $classname, ' Files';
?>
</h1>

<p>
<?php
$url = '../upload/classes/' . $classid . '/';
if (is_dir($url)) {
    echo '<b>Click on a file to download it.</b><br><br>';

    if ($handle = opendir($url)) {
        while (false !== ($entry = readdir($handle))) {
            if ($entry != "." && $entry != "..") {
                $url2 = $url . $entry;
                echo "<a href = $url2>$entry</a><br>";
            }
        }
        closedir($handle);
    }
} else {
    echo 'No files are uploaded for this class.';
}
?>
</p>

<?php include '../includes/overall/footer.php'; ?>
