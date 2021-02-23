/*!
* FitVids 1.1
*
* Copyright 2013, Chris Coyier - http://css-tricks.com + Dave Rupert - http://daverupert.com
* Credit to Thierry Koblentz - http://www.alistapart.com/articles/creating-intrinsic-ratios-for-video/
* Released under the WTFPL license - http://sam.zoy.org/wtfpl/
*
*/
(function(a){
	a.fn.fitVids=function(b){
		var e={customSelector:null};
		if(!document.getElementById("fit-vids-style")){
			var d=document.head||document.getElementsByTagName("head")[0];
			var c=".fluid-width-video-wrapper{width:100%;position:relative;padding:0;}.fluid-width-video-wrapper iframe,.fluid-width-video-wrapper object,.fluid-width-video-wrapper embed {position:absolute;top:0;left:0;width:100%;height:100%;}";
			var f=document.createElement("div");
			f.innerHTML='<p>x</p><style id="fit-vids-style">'+c+"</style>";
			d.appendChild(f.childNodes[1])
		}
		if(b){
			a.extend(e,b)
		}
		return this.each(
			function(){
				var g=[
					"iframe[src*='player.vimeo.com']",
					"iframe[src*='youtube.com']",
					"iframe[src*='youtube-nocookie.com']",
					"iframe[src*='kickstarter.com'][src*='video.html']",
					"object",
					"embed",
					"iframe[src*='videomore.ru']", 
					"iframe[src*='ivi.ru']", 
					"iframe[src*='megogo.net']", 
					"div[id*='advideotviglevideo'"];
				if(e.customSelector){
					g.push(e.customSelector)
				}
				var h=a(this).find(g.join(","));
				h=h.not("object object");
				h.each(function(){
					var m=a(this);
					if(this.tagName.toLowerCase()==="embed"&&m.parent("object").length||m.parent(".fluid-width-video-wrapper").length){return}
					var i=(this.tagName.toLowerCase()==="object"||(m.attr("height")&&!isNaN(parseInt(m.attr("height"),10))))?parseInt(m.attr("height"),10):m.height(),j=!isNaN(parseInt(m.attr("width"),10))?parseInt(m.attr("width"),10):m.width(),k=i/j;
					if(!m.attr("id")){
						var l="fitvid"+Math.floor(Math.random()*999999);
						m.attr("id",l)
					}
					m.wrap('<div class="fluid-width-video-wrapper"></div>').parent(".fluid-width-video-wrapper").css("padding-top",(k*100)+"%");
					m.removeAttr("height").removeAttr("width")
				})
			}
		)
	}
})(window.jQuery||window.Zepto);