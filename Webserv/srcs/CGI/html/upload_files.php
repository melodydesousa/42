<!DOCTYPE html>
<html>
  <head>
    <style>
      @import url("https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Hind:wght@400;700&display=swap");
      body {
        width: 70%;
        margin: 0 auto;
        background-color: #298ea0;
      }
      h1 {
        font-family: "Hind", sans-serif;
		font-size: 35px;
      }
      .box {
        margin: 0 auto;
        display: flex;
        flex-direction: column;
        height: 700px;
        justify-content: center;
        justify-items: center;
        /* border: 1px solid blue; */
      }
      .text {
        opacity: 0.5;
        line-height: 100%;
        align-self: center;
        /* border: 1px solid red; */
        text-align: center;
        display: inline-block;
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
      /* .text_two {
			  display: flex;
			  text-align: center;
			  display: inline-block;
			  margin: 0 auto;
			  font-size: 7px;
			  line-height: 0%;
			  font-family: "Didact Gothic", sans-serif;
			} */
    </style>
    <meta charset="utf-8" />
    <title>Upload</title>
    <link
      href="https://profile.intra.42.fr/assets/42_logo_black-684989d43d629b3c0ff6fd7e1157ee04db9bb7a73fba8ec4e01543d650a1c607.png"
      rel="icon"
      type="image/png"
    />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
  </head>
  <body>
    <div class="box">
      <div class="img">
	  <a href="index.html">
        <!-- <img
          src="../img/webserv.png"
          alt="logo"
		  src="./index.html"
          class="logo"
        /> -->
	</a>
      </div>
      <div class="text">
        <h1>Upload a File</h1>
      </div>
      <div class="text">
	  <form action="upload_process.php" method="post" enctype="multipart/form-data">
  			Select file to upload: <br><br>
  			<input type="file" name="fileToUpload" id="fileToUpload">
			<br><hr>
  			<input type="submit" value="Send it to the serv" name="submit">
		</form>
    <br><br> <- <a href="index.html">Home</a>
		</div>
    </div>
  </body>
</html>
