<?php
class Database
{
    protected $dsn, $options;

    protected $username = 'root';
    protected $password = '';

    private $host = 'localhost';
    private $databaseName = 'gallery_module';
    private $charset = 'utf8';

    public $pdo;

    function __construct()
    {
        $this->dsn = "mysql:host=$this->host;dbname=$this->databaseName;charset=$this->charset";
        $this->options = [
            PDO::ATTR_ERRMODE               => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE    => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES      => false,
        ];

        try {
            $this->pdo = new PDO($this->dsn,
                                 $this->username,
                                 $this->password,
                                 $this->options);
        } catch (PDOException $error) {
            echo $error->getMessage();
        }
    }
}
