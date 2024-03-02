<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Money Display 2</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 600px;
            margin: 20px auto;
            background-color: #fff;
            padding: 20px;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        h1 {
            text-align: center;
            color: #333;
        }
        .money {
            font-size: 24px;
            font-weight: bold;
            text-align: center;
            color: #4CAF50;
            margin-top: 20px;
        }
        .button-container {
            text-align: center;
            margin-top: 20px;
        }
        .button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: #fff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }
        .button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Money Display card 1</h1>
        <div class="money">
            <?php
                include("connect.php");
                $sql = "SELECT coin FROM test0 WHERE id = 1";
                $r = mysqli_query($con, $sql);
                if (!$r) {
                    die("Error in SQL query: " . mysqli_error($con));
                }
                $row = mysqli_fetch_row($r);
                if ($row) {
                    $money2 = $row[0];
                    echo "Money: " . $money2; // Displaying money value with a dollar sign
                } else {
                    echo "No money found!";
                }
                mysqli_close($con); // Close the database connection
            ?>
        </div>
        <div class="button-container">
            <button class="button" onclick="window.location.href='display2.php'">Open Display 1</button>
        </div>
    </div>
</body>
</html>
