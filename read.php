<?php
$user = $_GET['user'] ?? '';
include("connect.php");
if (!empty($user)) {
    $sql = "SELECT coin FROM test0 WHERE id = ?";
    $stmt = mysqli_prepare($con, $sql);
    mysqli_stmt_bind_param($stmt, 'i', $user);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_bind_result($stmt, $money1);
    mysqli_stmt_fetch($stmt);
    mysqli_stmt_close($stmt);
    if (isset($money1)) {
        echo "User " . $user . " has " . $money1 . " coins.<br>";
    } else {
        echo "User " . $user . " not found or has no coins.<br>";
    }
} else {
    echo "Invalid user parameter.<br>";
}
mysqli_close($con);
?>
