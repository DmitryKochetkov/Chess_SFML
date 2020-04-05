//
// Created by dimedrol on 05.04.2020.
//

#ifndef WWTBAM_SFML_GROUP_H
#define WWTBAM_SFML_GROUP_H


#ifndef GROUP_INCLUDED_HPP
#define GROUP_INCLUDED_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class Group : public sf::Drawable {
public:
    Group();
    virtual ~Group() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const sf::Drawable& operator[](std::size_t index); //TODO: убрать, если не используется
    std::size_t push_back(const sf::Drawable& drawable);
    const sf::Drawable& pop_back(); //TODO: удалять нужный элемент, а не последний

private:
    std::vector<std::reference_wrapper<const sf::Drawable>> m_drawables;
};

#endif


#endif //WWTBAM_SFML_GROUP_H
