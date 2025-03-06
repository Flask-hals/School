class Person
    def initialize(brand, zipcode, license, gender, age)
        @total = 0
        @brand = brand
        @zipcode = zipcode.to_s
        @license = license.to_i

        if gender == "M"
            @gender = "Male"
        elsif gender == "F"
            @gender = "Female"
        else
            @gender = gender
        end

        @age = age.to_i
    end

    def evaluate_policy(filename)
        self.instance_eval(File.read(filename))
        calculate
        @total.round(2)
    end

    def calculate
        if @gender == "Male" && @license < 3
            @total *= 0.9
        end
        if @brand == "Volvo" && @zipcode[0, 2] == "58"
            @total *= 1.2
        end
    end


    def method_missing(name, *args)
        if name == @brand.to_sym || name == @gender.to_sym
            @total += args[0]
        elsif name == :license
            if args[0].include?(@license)
                @total += args[1]
            end
        elsif name == :zipcode
            if args[0] == @zipcode.to_i
                @total += args[1]
            end
        elsif name == :agespan
            if args[0].include?(@age)
                @total += args[1]
            end
        end
    end
end


per = Person.new("Volvo","58435",2,"M",32)
p per.evaluate_policy("policy.rb")