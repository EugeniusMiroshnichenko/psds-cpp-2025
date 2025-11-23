constexpr double operator""_m_to_cm(long double meters){
    return meters * 100;
}

constexpr double operator""_cm_to_m(long double centimeter){
    return centimeter / 100.0;
}

constexpr double operator""_ft_to_m(long double feets){
    return feets * 0.3048;
}

constexpr double operator""_ft_to_cm(long double feets){
    return operator""_m_to_cm(operator""_ft_to_m(feets));
}

constexpr double operator""_ft_to_in(long double feets){
    return feets * 12.0;
}

constexpr double operator""_in_to_m(long double inches){
    return inches * 0.0254;
}

constexpr double operator""_in_to_cm(long double inches){
    return operator""_m_to_cm(operator""_in_to_m(inches));
}

constexpr double operator""_in_to_ft(long double inches){
    return inches / 12.0;
}

constexpr double operator""_m_to_ft(long double meters){
    return meters * 3.280839895;
}

constexpr double operator""_m_to_in(long double meters){
    return meters * 39.37007874;
}

constexpr double operator""_cm_to_ft(long double centimeters){
    return operator""_cm_to_m(operator""_m_to_ft(centimeters));
}

constexpr double operator""_cm_to_in(long double centimeters){
    return operator""_cm_to_m(operator""_m_to_in(centimeters));
}