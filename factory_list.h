#ifndef FACTORY_LIST_H
#define FACTORY_LIST_H

template <typename T>
class factory_list
{
	public:
		QVector<T *> &get_factories(){ return factories; }
		T *get_factory(QString name)
		{
			for(auto factory : factories){
				if(factory->name == name){
					return factory;
				}
			}
			return nullptr;
		}

		void add_factory(T *factory){ factories.append(factory); }
	private:
		QVector<T *> factories;
};

#endif // FACTORY_LIST_H
