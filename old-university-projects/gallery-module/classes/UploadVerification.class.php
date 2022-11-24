<?php
class UploadVerification
{
    protected static $allowedExtensions = array('png', 'jpg', 'jpeg', 'gif', 'JPG', 'JPEG', 'GIF', 'PNG');
    protected static $allowedMIMETypes = array('image/png', 'image/jpeg', 'image/gif');
    protected static $allowedExifTypes = array(IMAGETYPE_PNG, IMAGETYPE_JPEG, IMAGETYPE_GIF);

    public static $maxSizeKiB = 10000;
    public static $minSizeKiB = 0;

    public static function allowed_extension($fileName)
    {
        if (in_array(pathinfo($fileName)['extension'], self::$allowedExtensions)) {
            return true;
        } else return false;
    }

    public static function allowed_size($fileSize)
    {
        if ($fileSize < self::$minSizeKiB*1024) {
            return false;
        }

        if ($fileSize > self::$maxSizeKiB*1024) {
            return false;
        }

        return true;
    }

    public static function validate_image($file)
    {
        $fileInfo = finfo_open(FILEINFO_MIME_TYPE);
        if (!in_array(finfo_file($fileInfo, $file), self::$allowedMIMETypes)) {
            return false;
        }

        $detectedType = exif_imagetype($file);
        if (!in_array($detectedType, self::$allowedExifTypes)) {
            return false;
        }

        if ($detectedType == IMAGETYPE_PNG) {
            $recreated = @imagecreatefrompng($file);
        } elseif ($detectedType == IMAGETYPE_JPEG) {
            $recreated = @imagecreatefromjpeg($file);
        } elseif ($detectedType == IMAGETYPE_GIF) {
            $recreated = @imagecreatefromgif($file);
        }

        if (!$recreated) {
            return false;
        } else {
            imagedestroy($recreated);
        }

        return true;
    }
}
