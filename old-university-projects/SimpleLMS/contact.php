<?php include 'core/init.php'; ?>
<?php include 'includes/overall/header.php'; ?>

<head>
<link rel="stylesheet" type="text/css" href="assets/contactform/bootstrap.css">
</head>

<h1>Contact</h1>

<p>

<?php
$action=$_REQUEST['action'];
if ($action=="") {
    echo ('<strong>
    Type in "admin" to "Username to contact" field to contact the site administrator.
    <br>
    Type in instructor username to "Username to contact" field to contact a specific instructor.
    </strong>
    <br>
    <br>');
?>
    <form  action="" method="POST" enctype="multipart/form-data">
    <input type="hidden" name="action" value="submit">
    <div class="input-group input-group-lg">
    <span class="input-group-addon"><i class="glyphicon glyphicon-circle-arrow-right"></i></span>
    <input name="username" type="text" class="form-control" placeholder="Username to contact">
    </div>
    <br>
    <div class="input-group input-group-lg">
    <span class="input-group-addon"><i class="glyphicon glyphicon-envelope"></i></span>
    <input name="email" type="email" class="form-control" placeholder="Your email address">
    </div>
    <br>
    <div class="input-group input-group-lg">
    <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
    <input name="name" type="text" class="form-control" placeholder="Your name">
    </div>
    <br>
    <div class="input-group input-group-lg">
    <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
    <textarea name="message" class="form-control" placeholder="Your message"></textarea>
    </div>
    <br>
    <br>
    <div class="input-group input-group-lg">
    <input type="submit" class="form-control btn-primary" value="Send Message">
    </div>
    </form>
<?php
} else {
    $username = $_REQUEST['username'];
    $email_recipient = email_from_username($username);
    $name = $_REQUEST['name'];
    $email = $_REQUEST['email'];
    $message = $_REQUEST['message'];
    
    if (user_exists($username) === false) {
        echo "<div class='alert alert-danger'><span class='glyphicon glyphicon-exclamation-sign'></span> &nbsp; Username you entered does not exist. <a href='contact.php'>Please try again</a>.</div>";
    } elseif (filter_var($email, FILTER_VALIDATE_EMAIL) === false) {
        echo "<div class='alert alert-danger'><span class='glyphicon glyphicon-exclamation-sign'></span> &nbsp; Email address you entered is not valid. <a href='contact.php'>Please try again</a>.</div>";
    } elseif (($name == "")||($email == "")||($message == "")||($email_recipient == "")) {
        echo "<div class='alert alert-danger'><span class='glyphicon glyphicon-exclamation-sign'></span> &nbsp; All fields are required, some were left empty. <a href='contact.php'>Please try again</a>.</div>";
    } else {
        $from="From: $name<$email>\r\nReturn-path: $email";
        $subject="Message sent using SimpleLMS contact form";
        mail($email_recipient, $subject, $message, $from);
        echo "<div class='alert alert-success'><span class='glyphicon glyphicon-send'></span> &nbsp; Success! Message sent.</div>";
    }
}
?>
</p>

<?php include 'includes/overall/footer.php'; ?>
