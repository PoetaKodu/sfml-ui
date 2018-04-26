#pragma once

#include SFMLUI_PCH

namespace sfui
{

// Aliases for pointer type names:
template <typename TType>
using WeakPtr = std::weak_ptr<TType>;
template <typename TType>
using SharedPtr = std::shared_ptr<TType>;
template <typename TType, typename TDeleter = std::default_delete<TType>>
using UniquePtr = std::unique_ptr<TType, TDeleter>;

}