<!DOCTYPE html>
<html>
  <head>
    <style>
      @import url("https://fonts.googleapis.com/css2?family=Didact+Gothic&family=Hind:wght@400;700&display=swap");
      body {
        width: 70%;
        margin: 0 auto;
        background-color: #e9d5f1;
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
    <title>Post Form</title>
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
        <h1>Try the Post Form</h1>
      </div>
      <div class="text">
	  <form action="Formulaire_post.php" method="post">
      <ul>
        <label for="name">User:</label>
        <input type="text" id="name" name="user_name" />
      </ul>
      <ul>
        <label for="mail">Mail:</label>
        <input type="email" id="mail" name="user_email" />
      </ul>
      <ul>
        <label for="msg">Msg:</label>
        <input id="message" name="user_message"></input>
      </ul>
      <ul>
        <button type="submit">Send your message</button>
      </ul>
   
	<?php  if (!empty($_POST)) { ?>
	  User : <?php echo htmlspecialchars($_POST['user_name']); ?><br>
	  Mail : <?php echo htmlspecialchars($_POST['user_email']); ?><br>
	  Msg : <?php echo htmlspecialchars($_POST['user_message']); ?><br>
	
	<?php } ?>
	
  </form>
  <br><br> <- <a href="index.html">Home</a>
		</div>
    </div>
  </body>
</html>
