package json;

public enum PegColor {
    BLUE
    {
        @Override
        public String toString()
        {
            return "BLUE";
        } 
    },
    GREEN
    {
        @Override
        public String toString()
        {
            return "GREEN";
        } 
    },
    WHITE
    {
        @Override
        public String toString()
        {
            return "WHITE";
        } 
    },
    PINK
    {
        @Override
        public String toString()
        {
            return "PINK";
        } 
    },
    ORANGE
    {
        @Override
        public String toString()
        {
            return "ORANGE";
        } 
    },
    BLACK
    {
        @Override
        public String toString()
        {
            return "BLACK";
        } 
    },
    RED
    {
        @Override
        public String toString()
        {
            return "RED";
        } 
    },
    YELLOW{
        @Override
        public String toString()
        {
            return "YELLOW";
        } 
    },
    PURPLE
    {
        @Override
        public String toString()
        {
            return "PURPLE";
        } 
    };

    public static PegColor returnPegColorEnum(String color)
        throws InvalidColorException
    {
        switch(color)
        {
            case "BLUE"     :   return PegColor.BLUE;
            case "GREEN"    :   return PegColor.GREEN;
            case "WHITE"    :   return PegColor.WHITE;
            case "PINK"     :   return PegColor.PINK;
            case "ORANGE"   :   return PegColor.ORANGE;
            case "BLACK"    :   return PegColor.BLACK;
            case "RED"      :   return PegColor.RED;
            case "YELLOW"   :   return PegColor.YELLOW;
            case "PURPLE"   :   return PegColor.PURPLE;
            default         :   throw new InvalidColorException("color not valid: " + color);
        }
    }
}