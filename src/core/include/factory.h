#pragma once

#include <unordered_map>
#include <functional>

namespace Core {

	template <typename KeyType, typename ReturnType, typename Hash = std::hash<KeyType>>
	class Factory
		/*!
		* \class Factory
		* \brief Defines a simple static factory that can take any kind of data.
		*
		* \author L3nn0x
		* \date october 2016
		*/
	{
	public:
		Factory(const Factory&) = delete;
		Factory(Factory&&) = delete;
		Factory() = delete;

		template <typename... Args>
		static ReturnType create(const KeyType& key, Args&&... args) {
			const auto& res = getAssociations<Args...>().find(key);
      if (res == getAssociations<Args...>().end())
        return ReturnType{};
      return res->second(std::forward<Args>(args)...);
		}

		template <typename... Args>
		struct Initializer {
			Initializer(const KeyType& key, std::function<ReturnType(Args...)> f) {
				getAssociations<Args...>()[key] = f;
			}
		};

	private:
		template <typename... Args>
		static std::unordered_map<KeyType, std::function<ReturnType(Args...)>, Hash>& getAssociations() {
			static std::unordered_map<KeyType, std::function<ReturnType(Args...)>, Hash> associations;
			return associations;
		}
	};

}
