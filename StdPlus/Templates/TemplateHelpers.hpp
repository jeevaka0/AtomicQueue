/* Created by Jeevaka Dassanayake on 3/28/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {

	template<class T> auto operator<<( std::ostream& os, const T& t) -> decltype( t.print( os ), os )
	{
		t.print( os );
		return os;
	}

	template<class T> auto operator>>( std::istream& is, T& t) -> decltype( t.read( is ), is )
	{
		t.read( is );
		return is;
	}


	class TemplateHelpers {
	public :


	protected :
		// Typedefs


		// Methods


		// Data
	};
}
