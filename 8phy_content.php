<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

$directory = 'D:/XAMAPP/htdocs/test_site/8/phy';

// Ensure the directory path is valid and exists
if (is_dir($directory)) {
    // Scan the directory for files
    $files = scandir($directory);
    
    // Loop through files
    foreach ($files as $file) {
        // Exclude '.' and '..' directories and check for file type
        if ($file !== '.' && $file !== '..') {
            $filePath = $directory . '/' . $file;
            
            // Check if it's a file (not a directory)
            if (is_file($filePath)) {
                // Get file extension
                $fileExtension = pathinfo($filePath, PATHINFO_EXTENSION);
                
                // Check if the file is a video or PDF
                $allowedExtensions = ['mp4', 'avi', 'mov', 'pdf'];
                if (in_array(strtolower($fileExtension), $allowedExtensions)) {
                    // Generate a link to the file
                    $relativePath = str_replace('D:/XAMAPP/htdocs/', '', $filePath); // Adjust the path to be relative to the root
                    echo "<li><a href='/$relativePath' target='_blank'>" . htmlspecialchars($file) . "</a></li>";
                }
            }
        }
    }
} else {
    echo "<li>No content available</li>";
}
?>
