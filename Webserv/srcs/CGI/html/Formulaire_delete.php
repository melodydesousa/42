<!DOCTYPE html>
<html>
  <head>
  <style>
      @import url("https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Hind:wght@400;700&display=swap");
      body {
        width: 70%;
        margin: 0 auto;
        background-color: #e9d5f1;
		overflow: auto;

      }
      h1 {
        font-family: "Hind", sans-serif;
		font-size: 35px;
      }
      .box {
        margin: 0 auto;
        display: flex;
        flex-direction: column;
        /* height: 700px; */
        justify-content: center;
        justify-items: center;
        /* border: 1px solid blue; */
      }
      .text {
        /* opacity: 0.5; */
        line-height: 100%;
        align-self: center;
        /* border: 1px solid red; */
        text-align: center;
        display: inline-block;
      }
	  .text2 {
        /* line-height: 100%; */
        /* opacity: 0.5; */

        /* align-self: center; */
        text-align: center;
        /* display: inline-block; */
        /* border: 1px solid red; */
      }
	  ul
	  {
		padding-left: 0px;

	  }
      .line {
        height: 1px;
        background-color: black;
        margin: 1rem;
        opacity: 0.3;
      }
      .img {
        width: auto;
        margin: 0 auto;
        /* border: 1px solid green; */
      }


	  body {
        font-family: "Hind", sans-serif;
        text-align: center;
        padding-top: 100px;
		width: 90%;
        margin: 0 auto;
        background-color: #e9d5f1;
      }

			</style>
    <meta charset="utf-8" />
    <title>Form Delete</title>
    <link
      href="https://profile.intra.42.fr/assets/42_logo_black-684989d43d629b3c0ff6fd7e1157ee04db9bb7a73fba8ec4e01543d650a1c607.png"
      rel="icon"
      type="image/png"
    />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
  </head>
  <body>
    <div class="box">
      <div class="text" style="opacity: 0.5">
        <!-- <form action="Formulaire_delete.php" method="GET"> -->
        <h1>Delete a file from the Folder</h1>
      </div>
      <div class="text2">

      <?php
      $files = scandir('/mnt/nfs/homes/cfontain/Documents/Cursus/webserv/srcs/CGI/upload');
      foreach ($files as $file) {
          if ($file !== "." && $file !== ".." && $file !== ".gitkeep") {
              echo "<div id=\"text\">";
              echo "$file <br><br>\n\n";
              echo "<button type=\"button\" id=\"del_button\" onclick=\"deleteSomething('/upload/$file')\">";
              echo "Delete this file</button>";
              echo "</div>";
              echo "<br>";
          }
      }
      ?>
      
      <script>
          async function deleteSomething(path) {
              try {
                  await doDelete(path);
                  window.location.reload();
              } catch (error) {
                  alert(error.message);
              }
          }
        
          async function doDelete(path) {
              const response = await fetch(path, { method: 'DELETE' });
              if (response.status !== 200) {
                  throw new Error(`Failed to delete file: ${response.statusText}`);
              }
          }
</script>
  <!-- </form> -->
</div>
</div><br><br> <- <a href="index.html">Home</a>
</body>
</html>
