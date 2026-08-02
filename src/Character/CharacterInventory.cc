#include "Character/CharacterInventory.h"

// std::optional<EquipmentSlots> Character::checkSlotIfEmpty( EquipmentSlots slot ) const {
//   if ( slot == EquipmentSlots::RING ) {
//     if ( !equipment_.find( EquipmentSlots::RING_1 )->second ) {
//       return EquipmentSlots::RING_1;
//     }
//     if ( !equipment_.find( EquipmentSlots::RING_2 )->second ) {
//       return EquipmentSlots::RING_2;
//     }
//     return std::nullopt;
//   }
//   if ( slot == EquipmentSlots::MISC ) {
//     static constexpr int MISC_FIRST_SLOT_ID = static_cast<int>( EquipmentSlots::MISC_1 );
//     static constexpr int MISC_LAST_SLOT_ID = static_cast<int>( EquipmentSlots::MISC_5 );
//     for ( int i = MISC_FIRST_SLOT_ID; i <= MISC_LAST_SLOT_ID; ++i ) {
//       auto actual_slot = static_cast<EquipmentSlots>( i );
//       if ( !equipment_.find( actual_slot )->second ) {
//         return actual_slot;
//       }
//     }
//     return std::nullopt;
//   }

//   if ( !equipment_.find( slot )->second ) {
//     return slot;
//   }
//   return std::nullopt;
// }