import Foundation

enum SequenceType: String, CaseIterable, Identifiable {
    case nonDecreasing = "Неубывающая"
    case nonIncreasing = "Невозрастающая"
    case random = "Произвольная"
    case homogeneous = "Однородная"
    var id: String { self.rawValue }

    var englishValue: String {
        switch self {
        case .nonDecreasing:
            return "sort"
        case .nonIncreasing:
            return "inv"
        case .random:
            return "rand"
        case .homogeneous:
            return "equal"
        }
    }
}
