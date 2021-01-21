<!DOCTYPE html>
<html>
	<head>
		<title> Julia Set Generator </title>
	</head>
	<body>
		<canvas id="myCanvas" width="1200" height="600" style="border:1px solid #000000;"></canvas><br>
		<button onclick="draw()"> Render </button>
	</body>
	<script>
			
		var c = document.getElementById("myCanvas");
		var ctx = c.getContext("2d");

		var zoom = 1;
		var x0 = -2*(1/zoom);
		var y0 = -1*(1/zoom);
		var x1 = 2*(1/zoom);
		var y1 = 1*(1/zoom);
		var n = 2000;
		var dx = (x1-x0)/n;
		var dy = (y1-y0)/n;
		var renderThickness = 1;
		var convergenceRadius = 10;
		var numIt = 200;
		var p = [0.05,0.8];
		var blur = 0.5;


		function draw(){
			ctx.clearRect(0, 0, c.width, c.height);
			for(var x=x0; x<=x1; x+=dx){
				for(var y=y0; y<=y1; y+=dy){
					//if point converges, draw it
					
					var px = ((x-x0)/(x1-x0))*1200;
					var py = 600-((y-y0)/(y1-y0))*600;
					ctx.fillStyle = converges(x,y);
					ctx.fillRect(px,py,renderThickness,renderThickness);	
					
				}
			}
		}

		function f(z){
			var real = (z[0]*z[0])-(z[1]*z[1])+p[0];
			var imag = 2*z[0]*z[1]+p[1];
			var l = [real,imag];
			return l;
		}
		function mag(z){
			return Math.sqrt(z[0]*z[0]+z[1]*z[1]);
		}

		function halfSigmoid(x){
			if(x<convergenceRadius)	return 1/(1+Math.pow(Math.E,-1*(x-blur*convergenceRadius)));
			return 1;
		}

		function converges(x,y){
			var Z = [x,y];
			for(var i=0; i<numIt; i++){Z=f(Z); if(mag(Z)>convergenceRadius) break; }
			var colorProp = 1-halfSigmoid(mag(Z));
			var colorProp = Math.round(255*colorProp);
			return rgbToHex(colorProp,0,0);	
			
			

		}

		function componentToHex(c) {
		  var hex = c.toString(16);
		  return hex.length == 1 ? "0" + hex : hex;
		}

		function rgbToHex(r, g, b) {
		  return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
		}


	</script>
</html>