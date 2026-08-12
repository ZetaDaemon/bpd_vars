from enum import IntEnum


class EBinaryMathOperation:
    class EBoolResult(IntEnum):
        BoolBool_XNOR = 2
        BoolBool_AND = 3
        BoolBool_OR = 4
        BoolBool_XOR = 5
        FloatFloat_Equal = 6
        FloatFloat_Greater = 7
        FloatFloat_GreaterEqual = 8
        FloatFloat_Less = 9
        FloatFloat_LessEqual = 10
        FloatFloat_NotEqual = 11
        IntInt_Equal = 12
        IntInt_Less = 13
        IntInt_LessEqual = 14
        IntInt_Greater = 15
        IntInt_GreaterEqual = 16
        IntInt_NotEqual = 17
        ObjectObject_Equal = 18
        ObjectObject_NotEqual = 19

    class EIntResult(IntEnum):
        IntInt_Add = 2000002
        IntInt_Subtract = 2000003
        IntInt_Mult = 2000004
        IntInt_Divide = 2000005
        IntInt_Power = 2000006
        IntInt_RandomRange = 1000007
        IntInt_Average = 2000008
        IntInt_Min = 2000009
        IntInt_Max = 2000010

    class EFloatResult(IntEnum):
        FloatFloat_Add = 2000002
        FloatFloat_Subtract = 2000003
        FloatFloat_Mult = 2000004
        FloatFloat_Divide = 2000005
        FloatFloat_Power = 2000006
        FloatFloat_RandomRange = 2000007
        FloatFloat_Average = 2000008
        FloatFloat_Min = 2000009
        FloatFloat_Max = 2000010
        VectorVector_Dot = 2000011
        VectorVector_Distance = 2000012

    class EVectorResult(IntEnum):
        VectorVector_Add = 3000002
        VectorVector_Subtract = 3000003
        VectorVector_Divide = 3000004
        VectorVector_Multiply = 3000005
        VectorVector_Project = 3000006
        VectorVector_Cross = 3000007
        VectorVector_NormalizeDifference = 3000008
        VectorVector_Rotate = 3000009


class EUnaryMathOperation:
    class EBoolOperation(IntEnum):
        IsTruthy = 1
        IsFalsey = 2
        ToFloat = 1000001
        ToInt = 2000001
        ToVector = 3000001

    class EIntOperation(IntEnum):
        IsTruthy = 1
        IsFalsey = 2
        ToFloat = 1000001
        Value = 2000001
        Negate = 2000006
        Abs = 2000007
        ToVector = 3000001

    class EFloatOperation(IntEnum):
        IsTruthy = 1
        Negate = 1000002
        Abs = 1000003
        Cos = 1000008
        Sin = 1000009
        Tan = 1000010
        IntRound = 2000001
        IntRoundDown = 2000002
        IntRoundUp = 2000003
        IntRoundAlt = 2000004
        IntTruncate = 2000005
        ToVector = 3000001

    class EVectorOperation(IntEnum):
        IsTruthy = 1
        Magnitude = 1000001
        X = 1000004
        Y = 1000005
        Z = 1000006
        MagnitudeAlt = 1000007
        MagnitudeIntRound = 2000001
        MagnitudeIntRoundDown = 2000002
        MagnitudeIntRoundUp = 2000003
        MagnitudeIntRoundAlt = 2000004
        MagnitudeIntTruncate = 2000005
        Negate = 3000002
        Normalize = 3000003
        Abs = 3000004

    class EObjectOperation(IntEnum):
        IsTruthy = 1
        ToFloat = 1000001
        """Calls ObjToFloat.

        If the object is not a PrimitiveComponent, it returns 0.0
        Otherwise:
            max(Scale3D.X, Scale3D.Y, Scale3D.Z) * Scale
        """

        IsValidInt = 2000001
        VectorIfValid = 3000001
        """If valid returns a vector of all 1's, otherwise it's all 0's."""
