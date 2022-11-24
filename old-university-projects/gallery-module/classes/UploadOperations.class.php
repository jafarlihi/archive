<?php
class UploadOperations
{
    protected $POST;
    protected $FILES;

    protected $thumbnailDirectory = 'images/thumb';
    protected $fullSizeDirectory = 'images/full';

    public $thumbResX = 200;
    public $thumbResY = 150;
    public $fullSizeResX = 1200;
    public $fullSizeResY = 900;

    function __construct($POST, $FILES)
    {
        $this->POST = $POST;
        $this->FILES = $FILES;
        self::error_checkpoint();
    }

    public function debug_print_input()
    {
        print_r ($this->POST);
        print_r ($this->FILES);
    }

    protected function error_checkpoint()
    {
        $errorTemplate = <<<'EOT'
        <div class="alert alert-danger alert-dismissible col-md-6" role="alert">
          <button type="button" class="close" data-dismiss="alert"><span>&times;</span></button>
          <strong>Error!</strong> %1$s
        </div>
EOT;

        $notFilled = 'Tags are not specified and/or image that is to be uploaded is not chosen.';
        $wrongExtension = 'Given file\'s extention is not allowed. Only .jpeg, .jpg, .png, .gif are accepted.';
        $wrongSize = 'Given file is too big. Maximum %sKiB is allowed.';
        $notImage = 'Given file is not an image file. Please try re-uploading another file.';

        $wrongSize = sprintf($wrongSize, UploadVerification::$maxSizeKiB);

        if (empty($this->POST['tags']) || empty($this->FILES['image']['tmp_name'])) {
            echo sprintf($errorTemplate, $notFilled);
            return false;
        }

        if (!UploadVerification::allowed_extension($this->FILES['image']['name'])) {
            echo sprintf($errorTemplate, $wrongExtension);
            return false;
        }

        if (!UploadVerification::allowed_size($this->FILES['image']['size'])) {
            echo sprintf($errorTemplate, $wrongSize);
            return false;
        }

        if (!UploadVerification::validate_image($this->FILES['image']['tmp_name'])) {
            echo sprintf($errorTemplate, $notImage);
            return false;
        }

        self::operator();
    }

    protected function operator()
    {
        $db = new Database();

        $lastID = 0;

        $statement = $db->pdo->query('SELECT * FROM images ORDER BY id DESC LIMIT 1');
        while ($row = $statement->fetch()) {
            $lastID = $row['id'];
        }

        $lastID++;

        $imageUploader = new ImageOperations($this->FILES['image'], $lastID);

        $tags = str_replace('"', ' ', $this->POST['tags']);
        $tags = str_replace('\'', ' ', $tags);
        $tags = str_replace(';', ' ', $tags);
        $tags = htmlspecialchars($tags);
        $tags = filter_var($tags, FILTER_SANITIZE_STRING);

        $tagsArray = explode(',', $tags);
        $tagsJSON = json_encode($tagsArray);

        $statement = $db->pdo->prepare('INSERT INTO images (id, tags) VALUES (:id, :tags)');
        $statement->execute(array(
            "id" => $lastID,
            "tags" => $tagsJSON
        ));

        $successMessage = <<<'EOT'
        <div class="alert alert-success alert-dismissible col-md-6" role="alert">
          <button type="button" class="close" data-dismiss="alert"><span>&times;</span></button>
          <strong>Success!</strong> Your image was successfully uploaded!
        </div>
EOT;

        echo $successMessage;
    }
}
