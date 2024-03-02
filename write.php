<?php
  $money = $_GET['money'] ?? '';
  $user = $_GET['user'] ?? '';
  include("connect.php");
  $sql = "UPDATE test0 SET coin = ? WHERE id = ?";
  $stmt = mysqli_prepare($con, $sql);
  mysqli_stmt_bind_param($stmt, 'ii', $money, $user);
  $success = mysqli_stmt_execute($stmt);
  if ($success) {
    echo "User " . $user . " has " . $money . " coins.<br>";
  } else {
    echo "Error updating coins: " . mysqli_error($con);
  }
  mysqli_stmt_close($stmt);
  mysqli_close($con);
?>
