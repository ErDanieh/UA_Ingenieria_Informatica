<?php
$hostname = "192.168.56.222";
$username = "daniel";
$password = "270301";
$db = "asorc";
$dbconnect=mysqli_connect($hostname,$username,$password,$db);
if ($dbconnect->connect_error) {
die("Database connection failed: " . $dbconnect->connect_error);
}
?>
<table border="1" align="center">
<tr>
<td>Reviewer Name</td>
<td>Stars</td>
<td>Details</td>
</tr>
<?php
$query = mysqli_query($dbconnect, "SELECT * FROM alumnos")
or die (mysqli_error($dbconnect));
while ($row = mysqli_fetch_array($query)) {
echo
"<tr>
<td>{$row['id']}</td>
<td>{$row['nombre']}</td>
<td>{$row['apellido']}</td>
</tr>\n";
}
?>
