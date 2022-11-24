<?php include 'core/init.php'; ?>
<?php include 'includes/overall/header.php'; ?>

<h1>Site Statistics</h1>

<?php
$result = mysql_query("SELECT * FROM logins");
$num_rows = mysql_num_rows($result);
echo 'Registered accounts: ' . $num_rows;
?>
<br>

<?php
$result = mysql_query("SELECT * FROM classes");
$num_rows = mysql_num_rows($result);
echo 'Registered classes: ' . $num_rows;
?>
<br>

<?php
$result = mysql_query("SELECT * FROM participation");
$num_rows = mysql_num_rows($result);
echo 'Class enrollments: ' . $num_rows;
?>
<br>

<?php
$result = mysql_query("SELECT * FROM forums");
$num_rows = mysql_num_rows($result);
echo 'Message Board posts: ' . $num_rows;
?>
<br>

<?php
$f = 'upload';
$io = popen('/usr/bin/du -sk ' . $f, 'r');
$size = fgets($io, 4096);
$size = substr($size, 0, strpos($size, "\t"));
pclose($io);

if ($size > 1) {
    echo 'Total size of uploaded class files: ' . $size . 'KB';
} else {
    echo 'Total size of uploaded class files: 0KB';
}
?>

<?php include 'includes/overall/footer.php'; ?>
