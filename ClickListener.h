 #ifndef CLICKLISTENER_H
 #define CLICKLISTENER_H
 class Widget;
 class ClickListener {
 	public:
 	virtual void onClick(Widget * sender) = 0;
 	
 };
#endif
