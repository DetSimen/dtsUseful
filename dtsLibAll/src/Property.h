#pragma once
#include "Arduino.h"

template<typename T, typename C>
class TProperty {

	using PGetterFunc =  T(C::*)() const;
	using PSetterFunc =	 void (C::*)(T);

private:
	C*	const			fobject;
	PSetterFunc const	fsetter;
	PGetterFunc const	fgetter;

public:

	TProperty(C* AClass, PGetterFunc getFunc , PSetterFunc setFunc)
		:fobject(AClass),fsetter(setFunc),fgetter(getFunc) 	{}

	operator T() const
	{
		return (fobject->*fgetter)();
	}

	T operator = (T AValue) {
		if ((fsetter) != NULL) 	(fobject->*fsetter)(AValue);
		return AValue;
	}

};
