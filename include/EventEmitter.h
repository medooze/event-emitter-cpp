#ifndef MEDOOZE_EVENTEMITTER_H
#define MEDOOZE_EVENTEMITTER_H

#include <map>
#include <functional>
#include <memory>
#include <typeindex>

namespace medooze 
{

class EventEmitter
{
private:
	class BaseListener 
	{
	public:
		explicit BaseListener() = default;
		BaseListener(const BaseListener&) = delete;
		BaseListener& operator=(const BaseListener&) = delete;
		virtual ~BaseListener() {}
	};

	template<typename Type>
	class Listener : public BaseListener
	{
	public:
		explicit Listener(const std::function<void (Type&)> &callback) 
		{
			 this->callback = callback; 
		}
		Listener(const Listener&) = delete;
		Listener& operator=(const Listener&) = delete;
		virtual ~Listener(){}
		void emit(Type& type)  { callback(type); }		 
	private:
		std::function<void (Type&)> callback;
	};

public:
	template<typename Type>
	void emit(Type& type) 
	{
		auto& listener = listeners[typeid(type)];
		if (listener)
			static_cast<Listener<Type>*>(listener.get())->emit(type);
	}
	
	template<typename Type>
	EventEmitter& on(const std::function<void (Type&)> &callback) 
	{
		listeners[typeid(Type)] = std::unique_ptr<BaseListener>(new Listener<Type>(callback));
		return *this;
	}
private:
	std::map<std::type_index,std::unique_ptr<BaseListener>> listeners;
};

}; // namespace medooze

#endif /* EVENTEMITTER_H */

