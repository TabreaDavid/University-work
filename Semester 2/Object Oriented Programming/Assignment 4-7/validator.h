#pragma once
#include "domain.h"
#include "exceptions.h"

class Validator {
public:
    void validate(TrenchCoat coat) {
        if (coat.getSize().empty() || coat.getColour().empty() || coat.getPhoto().empty())
            throw ValidationException("Fields cannot be empty!");

        if (coat.getPrice() <= 0 || coat.getQuantity() < 0)
            throw ValidationException("Price must be > 0 and quantity >= 0!");
    }
};