<?php
class ImageOperations
{
    protected $imagePOST;
    protected $lastID;

    protected $imageWidth, $imageHeight, $imageFormat;

    protected $thumbDirectory = './images/thumb/';
    protected $fullSizeDirectory = './images/full/';
    protected $thumbWidth = 200;
    protected $fullSizeWidth = 1200;

    function __construct($imagePOST, $lastID)
    {
        $this->imagePOST = $imagePOST;
        $this->lastID = $lastID;
        list($this->imageWidth, $this->imageHeight, $this->imageFormat) = getimagesize($imagePOST['tmp_name']);
        self::process();
    }

    protected function process()
    {
        switch ($this->imageFormat) {
            case 1:
                $image = imagecreatefromgif($this->imagePOST['tmp_name']);
                break;
            case 2:
                $image = imagecreatefromjpeg($this->imagePOST['tmp_name']);
                break;
            case 3:
                $image = imagecreatefrompng($this->imagePOST['tmp_name']);
                break;
            default:
                echo 'Image format is not supported.';
        }

        self::upload_thumb($image);
        self::upload_fullSize($image);

        imagedestroy($image);
    }

    protected function upload_thumb(&$image) {
        $thumbHeight = floor($this->imageHeight * ($this->thumbWidth / $this->imageWidth));

        $thumbImage = imagecreatetruecolor($this->thumbWidth, $thumbHeight);
        imagecopyresampled($thumbImage, $image, 0, 0, 0, 0, $this->thumbWidth, $thumbHeight, $this->imageWidth, $this->imageHeight);

        imagejpeg($thumbImage, $this->thumbDirectory . $this->lastID . '.jpeg');
    }

    protected function upload_fullSize(&$image) {
        $fullSizeHeight = floor($this->imageHeight * ($this->fullSizeWidth / $this->imageWidth));

        $fullSizeImage = imagecreatetruecolor($this->fullSizeWidth, $fullSizeHeight);
        imagecopyresampled($fullSizeImage, $image, 0, 0, 0, 0, $this->fullSizeWidth, $fullSizeHeight, $this->imageWidth, $this->imageHeight);

        imagejpeg($fullSizeImage, $this->fullSizeDirectory . $this->lastID . '.jpeg');
    }
}
