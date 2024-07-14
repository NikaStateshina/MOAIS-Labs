import Foundation

struct FileGenerator {
    static func generateSequence(numberOfElements: Int, minDigits: Int, maxDigits: Int, sequenceType: SequenceType) throws -> [String] {
        var sequence: [String] = []

        for _ in 0..<numberOfElements {
            sequence.append(generateRandomNumber(minDigits: minDigits, maxDigits: maxDigits))
        }

        switch sequenceType {
        case .nonDecreasing:
            sequence.sort { Int($0)! < Int($1)! }
        case .nonIncreasing:
            sequence.sort { Int($0)! > Int($1)! }
        case .homogeneous:
            let homogeneousElement = generateRandomNumber(minDigits: minDigits, maxDigits: minDigits)
            sequence = Array(repeating: homogeneousElement, count: numberOfElements)
        case .random:
            sequence.shuffle()
        }

        return sequence
    }

    private static func generateRandomNumber(minDigits: Int, maxDigits: Int) -> String {
        let numberOfDigits = Int.random(in: minDigits...maxDigits)
        var number = String(Int.random(in: 1...9)) // Первая цифра не может быть нулем
        for _ in 1..<numberOfDigits {
            number.append(String(Int.random(in: 0...9)))
        }
        return number
    }

    static func generateFile(numberOfElements: Int, minDigits: Int, maxDigits: Int, sequenceType: SequenceType) throws -> String {
        let fileManager = FileManager.default

        // Получаем путь к рабочему столу
        if let desktopDirectory = fileManager.urls(for: .desktopDirectory, in: .userDomainMask).first {
            // Создаем директорию input на рабочем столе
            let directoryURL = desktopDirectory.appendingPathComponent("input")
            if !fileManager.fileExists(atPath: directoryURL.path) {
                try fileManager.createDirectory(at: directoryURL, withIntermediateDirectories: true, attributes: nil)
            }

            let fileName = "\(numberOfElements)\(sequenceType.englishValue)\(minDigits)-\(maxDigits).txt"
            let fileURL = directoryURL.appendingPathComponent(fileName)

            let sequence = try generateSequence(numberOfElements: numberOfElements, minDigits: minDigits, maxDigits: maxDigits, sequenceType: sequenceType)
            try sequence.joined(separator: " ").write(to: fileURL, atomically: true, encoding: .utf8)

            return fileName
        } else {
            throw NSError(domain: "FileGenerator", code: 1, userInfo: [NSLocalizedDescriptionKey: "Не удалось найти рабочий стол"])
        }
    }
}
