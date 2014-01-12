ofxNodeUI (ofxNUI)
==================

A 3D, Generative, Nodal User Interface for openFrameworks
---------------------------------------------------------

ofxNUI is an add-on for openFrameworks that allows for an easy, transparent user interface implementation experience. It takes away the hassle of worrying about widget positioning and combines easy-to-use 2D UI widgets with the non-confined, unlimited nature of recursive 3D space.

Features
--------

* 2D Widgets in 3D space
ofxNUI uses [Reza Ali’s comprehensive ofxUI](http://github.github.com/github-flavored-markdown/sample_content.html) for it’s 2D widget system. For those already familiar with Reza’s awesomely efficient UI framework, using this add-on will feel like a walk in the park.

Simply derive any classes you’d like implemented in your UI from ofxNUIWidgetNode and your canvas is setup automatically (WidgetNode derives from ofxUISuperCanvas!). Add widgets by typing “addWidgetName(args)”. Add children nodes by typing “addChild(ofxNUINode*)” or “addChildList(vector<ofxNUINode*>)”. ofxNUI will automatically handle the positioning of both your nodes and widgets. Add listeners like you normally do, or use the pre-prepared “WidgetFunctions(string _widgetName)” that is already set-up for you with each widgetNode.

ofxUI is implemented almost entirely through polymorphism, so unless there are any major framework changes, ofxNUI will always remain immediately up-to-date and compatible. If you do come across any compatibility issues, feel free to raise an issue and I’ll look into it.

* Multiple Node Layouts
Currently, different node layouts include:
- Radial (surrounds parent node in a circle)
- Spiral (same as radial, though spirals down the z-axis)
- List (forms a vertical list next to the parent)
- Grid (not yet implemented)
- YOUR OWN AMAZING LAYOUT IDEA!

* Multiple Node Shapes
- Spheres
- Circles
- Triangles
- YOUR OWN AMAZING SHAPES!

Help & Contribute!
------------------

This is an open project, so feel free to contribute your own node layouts, shapes and color schemes! The aim for this repository is to become a go-to, extensive, newbie/pro friendly framework for ridiculously easy (to the point where using it feels transparent) UI implementation. Anything that adds to this goal would be immensely appreciated!

Example(s) & Tute(s)
--------------------
COMING SOON

Inspiration
-----------
ofxNUI was heavily inspired by [Josh Parnell and his in-game nodal UI for Limit Theory](https://www.youtube.com/watch?v=ADcfqusFfaM) as well as [Reza Ali’s ofxUI](http://github.github.com/github-flavored-markdown/sample_content.html).

Required ofxAddons
------------------
* [ofxUI](https://github.com/rezaali/ofxUI) by Reza Ali
* [ofxTween](https://github.com/arturoc/ofxTween) by Arturo Castro & James George

Compatibility
-------------
The only testing that has occurred so far has been in Xcode 5, OSX 10.9, however 

Development Stage
-----------------
ofxNUI is still in its infancy, however is already entirely usable. Check the issues section to see my to-do list (and add your own!).