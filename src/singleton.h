#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template<class C>
class Singleton{
	public:
		Singleton()=default;
		Singleton(const Singleton& other) = delete;
		static std::shared_ptr<C> get(){
			static std::shared_ptr<C> s{new C};
			return s;
		}
	private:
};

#endif
