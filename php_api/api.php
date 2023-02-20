<?php

// Connect to the MySQL database
$host = "localhost";
$username = ".";
$password = ".";
$dbname = "home";
$conn = mysqli_connect($host, $username, $password, $dbname);

// Check the connection
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  // Get the temperature and humidity data from the POST request
  $temperature = $_POST['temperature'];
  $humidity = $_POST['humidity'];

  // Insert the temperature and humidity data into the MySQL database
  $sql = "INSERT INTO readings (temperature, humidity) VALUES ('$temperature', '$humidity')";
  if (mysqli_query($conn, $sql)) {
    echo "Temperature and humidity data added successfully";
  } else {
    echo "Error adding temperature and humidity data: " . mysqli_error($conn);
  }
}

// Close the connection
mysqli_close($conn);
