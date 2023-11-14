#include <memory>

namespace Clone::Utls
{
	/// <summary>
	/// Templated base class for declaring a singleton
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class Singleton
	{
	public:
		static T& Get()
		{
			s_context.Create();
			return *s_context.m_instance.get();
		}

		static void Delete()
		{
			s_context.Destroy();
		}


	protected:
		Singleton() = default;


	private:
		/// <summary>
		/// Class that contains the context of the singleton
		/// </summary>
		class Context
		{
		public:
			void Create()
			{
				if (m_instance == nullptr)
				{
					m_instance = std::make_unique<T>();
				}
			}

			void Destroy()
			{
				m_instance.reset();
			}

			~Context()
			{
				Destroy();
			}

		public:
			std::unique_ptr<T> m_instance{ nullptr };
		};

	private:
		static inline Context s_context;
	};
}