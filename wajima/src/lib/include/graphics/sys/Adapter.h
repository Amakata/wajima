#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include <string>
#include <vector>

#include <graphics/sys/Mode.h>

namespace zefiro_graphics {

	class Adapter 
	{
	public:
		Adapter( const int adapterNumber , const std::string name );
		virtual ~Adapter();
		std::string getName() const;
		int getAdapterNumber() const;
		void addMode( Mode mode );
		std::vector<Mode> getModeVector() const;
		std::string toString() const;
	private:
		std::string _name;
		int _adapterNumber;
		std::vector<Mode> _modes;
	};
};

#endif //_ADAPTER_H__