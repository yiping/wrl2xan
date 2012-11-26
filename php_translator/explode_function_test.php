<?php
$str = "    Hello world. It's a beautiful day. ";
$str_array = print_r (explode(" ", trim($str)));

var_dump($str_array);


$str = " Hello World! ";
echo "Without trim: [" . $str ."]\n";

echo "With trim: [" . trim($str) ."]\n";

?> 
