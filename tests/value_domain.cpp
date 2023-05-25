#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <common.hpp>

TEST_CASE("value_domain_T<float>::value_domain_T()",
          "[working][unittest][value_domain_T]")
{
	value_domain_T domain{0.0f, 1.0f};

	CHECK(domain.min() == 0.0f);
	CHECK(domain.max() == 1.0f);
}

TEST_CASE("value_domain_T constructions/assignation",
          "[working][unittest][value_domain_T]")
{
	{
		value_domain_T domain{1.2f, 5.25f};
		domain = value_domain_T{10.2f, 50.25f};

		CHECK(domain.min() == 10.2f);
		CHECK(domain.max() == 50.25f);
	}
	{
		value_domain_T domain0{1.2f, 5.25f};
		value_domain_T domain1 = domain0;

		CHECK(domain0.min() == 1.2f);
		CHECK(domain0.max() == 5.25f);
		CHECK(domain1.min() == 1.2f);
		CHECK(domain1.max() == 5.25f);
	}
	{
		value_domain_T domain0{1.2f, 5.25f};
		value_domain_T domain1 = std::move(domain0);

		CHECK(domain1.min() == 1.2f);
		CHECK(domain1.max() == 5.25f);
	}
	{
		value_domain_T domain0{1.2f, 5.25f};
		value_domain_T domain1{10.2f, 50.25f};
		domain1 = std::move(domain0);

		CHECK(domain1.min() == 1.2f);
		CHECK(domain1.max() == 5.25f);
	}
}

TEST_CASE("value_domain_T::value_domain_T(T lim0, T lim1)",
          "[working][unittest][value_domain_T]")
{
	value_domain_T domain1{1.2f, 5.25f};

	CHECK(domain1.lim0() == 1.2f);
	CHECK(domain1.lim1() == 5.25f);
	CHECK(domain1.min() == 1.2f);
	CHECK(domain1.max() == 5.25f);

	value_domain_T domain2{5.25f, 1.2f};

	CHECK(domain2.lim0() == 5.25f);
	CHECK(domain2.lim1() == 1.2f);
	CHECK(domain2.min() == 1.2f);
	CHECK(domain2.max() == 5.25f);
}

TEST_CASE("value_domain_T::clamp(T value)", "[working][unittest][value_domain_T]")
{
	{
		value_domain_T domain{1.2f, 5.25f};

		CHECK(domain.clamp(0.0f) == 1.2f);
		CHECK(domain.clamp(1.0f) == 1.2f);
		CHECK(domain.clamp(1.2f) == 1.2f);
		CHECK(domain.clamp(1.3f) == 1.3f);
		CHECK(domain.clamp(3.0f) == 3.0f);
		CHECK(domain.clamp(5.0f) == 5.0f);
		CHECK(domain.clamp(5.5f) == 5.25f);
		CHECK(domain.clamp(1000.0f) == 5.25f);
	}
}

TEST_CASE("value_domain_T::range()", "[working][unittest][value_domain_T]")
{
	CHECK(value_domain_T{0.0f, 1.0f}.range() == 1.0f);
	CHECK(value_domain_T{0.0f, 2.0f}.range() == 2.0f);
	CHECK(value_domain_T{1.0f, 2.0f}.range() == 1.0f);
	CHECK(value_domain_T{-1.0f, 2.0f}.range() == 3.0f);
	CHECK(value_domain_T{1.0f, 0.0f}.range() == 1.0f);
	CHECK(value_domain_T{2.0f, 0.0f}.range() == 2.0f);
	CHECK(value_domain_T{2.0f, 1.0f}.range() == 1.0f);
	CHECK(value_domain_T{2.0f, -1.0f}.range() == 3.0f);
}

TEST_CASE("value_domain_T::lerp(normalized_value_T value)",
          "[working][unittest][value_domain_T]")
{
	value_domain_T domain1{0.0f, 1.0f};

	CHECK(domain1.lerp(normalized_value_T(0.0f)) == domain1.lim0());
	CHECK(domain1.lerp(normalized_value_T(1.0f)) == domain1.lim1());
	CHECK(domain1.lerp(normalized_value_T(0.25f)) == 0.25f);
	CHECK(domain1.lerp(normalized_value_T(0.5f)) == 0.5f);
	CHECK(domain1.lerp(normalized_value_T(0.75f)) == 0.75f);
	CHECK(domain1.lerp(normalized_value_T(-145600.75f)) == domain1.lim0());
	CHECK(domain1.lerp(normalized_value_T(1000.75f)) == domain1.lim1());

	value_domain_T domain2{1.0f, 0.0f};

	CHECK(domain2.lerp(normalized_value_T(0.0f)) == domain2.lim0());
	CHECK(domain2.lerp(normalized_value_T(1.0f)) == domain2.lim1());
	CHECK(domain2.lerp(normalized_value_T(0.25f)) == 0.75f);
	CHECK(domain2.lerp(normalized_value_T(0.5f)) == 0.5f);
	CHECK(domain2.lerp(normalized_value_T(0.75f)) == 0.25f);
	CHECK(domain2.lerp(normalized_value_T(-145600.75f)) == domain2.lim0());
	CHECK(domain2.lerp(normalized_value_T(1000.75f)) == domain2.lim1());
}

TEST_CASE("normalized_value_T::normalized_value_T()",
          "[working][unittest][value_domain_T]")
{
	normalized_value_T v{0.0f};

	CHECK(v.value() == 0.0f);
}

TEST_CASE("normalized_value_T::normalized_value_T(value)",
          "[working][unittest][value_domain_T]")
{
	CHECK(normalized_value_T{0.0f}.value() == 0.0f);
	CHECK(normalized_value_T{0.5f}.value() == 0.5f);
	CHECK(normalized_value_T{1.0f}.value() == 1.0f);
	CHECK(normalized_value_T{-1.0f}.value() == 0.0f);
	CHECK(normalized_value_T{2.0f}.value() == 1.0f);
}

TEST_CASE("normalized_value_T assignation", "[working][unittest][value_domain_T]")
{
	normalized_value_T v{0.0f};
	CHECK(v.value() == 0.0f);

	v = 1.0f;
	CHECK(v.value() == 1.0f);

	v = 12.0f;
	CHECK(v.value() == 1.0f);

	v = 0.5f;
	CHECK(v.value() == 0.5f);

	v = 0.0f;
	CHECK(v.value() == 0.0f);

	v = -1000.0f;
	CHECK(v.value() == 0.0f);
}

TEST_CASE("unnormalized_value_T::unnormalized_value_T(value_domain_T[, value])",
          "[working][unittest][value_domain_T]")
{
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d};
		CHECK(v.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 0.0f};
		CHECK(v.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 1.0f};
		CHECK(v.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 2.0f};
		CHECK(v.value() == 2.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 1.5f};
		CHECK(v.value() == 1.5f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 1.984151f};
		CHECK(v.value() == 1.984151f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, 3.0f};
		CHECK(v.value() == 2.0f);
	}
}

TEST_CASE("unnormalized_value_T::setValue(value)",
          "[working][unittest][value_domain_T]")
{
	value_domain_T d{1.0f, 2.0f};
	unnormalized_value_T v{d};

	v.setValue(1.0f);
	CHECK(v.value() == 1.0f);
	v.setValue(1.5f);
	CHECK(v.value() == 1.5f);
	v.setValue(2.0f);
	CHECK(v.value() == 2.0f);
	v.setValue(0.0f);
	CHECK(v.value() == 1.0f);
	v.setValue(-50.0f);
	CHECK(v.value() == 1.0f);
	v.setValue(1.984151f);
	CHECK(v.value() == 1.984151f);
}

TEST_CASE("unnormalized_value_T::unnormalized_value_T(normalized_value_T)",
          "[working][unittest][value_domain_T]")
{
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{0.0f}};
		CHECK(v.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{1.0f}};
		CHECK(v.value() == 2.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{0.5f}};
		CHECK(v.value() == 1.5f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{1.0f / 3.0f}};
		CHECK(v.value() == Approx(1.33333333f));
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{10.0f}};
		CHECK(v.value() == 2.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T v{d, normalized_value_T{-10.0f}};
		CHECK(v.value() == 1.0f);
	}
}

TEST_CASE("normalized_value_T::normalized_value_T(unnormalized_value_T)",
          "[working][unittest][value_domain_T]")
{
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 1.0f};
		normalized_value_T n{u};
		CHECK(n.value() == 0.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 2.0f};
		normalized_value_T n{u};
		CHECK(n.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 0.0f};
		normalized_value_T n{u};
		CHECK(n.value() == 0.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 100.0f};
		normalized_value_T n{u};
		CHECK(n.value() == 1.0f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 1.5f};
		normalized_value_T n{u};
		CHECK(n.value() == 0.5f);
	}
	{
		value_domain_T d{1.0f, 2.0f};
		unnormalized_value_T u{d, 1.333333f};
		normalized_value_T n{u};
		CHECK(n.value() == Approx(0.3333333f));
	}
}

TEST_CASE("un-normalized_value_T_misc", "[working][unittest][value_domain_T]")
{
	{
		const value_domain_T d{1.0f, 2.0f};
		const unnormalized_value_T u0{d, 0.25f};
		const normalized_value_T n{u0};
		const unnormalized_value_T u1{d, n};
		CHECK(u0.value() == Approx(u1.value()).margin(1.0e-5));
	}
	{
		const value_domain_T d{42.0f, -47.3f};
		const unnormalized_value_T u0{d, 0.25f};
		const normalized_value_T n{u0};
		const unnormalized_value_T u1{d, n};
		CHECK(u0.value() == Approx(u1.value()).margin(1.0e-5));
	}
}
