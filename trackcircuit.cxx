#include "trackcircuit.hxx"

QMap<QString, EWRB::TrackCircuit*> EWRB::TrackCircuits(QWidget* parent) {
    QMap<QString, TrackCircuit*> blocks_ = {};
    QList<QString> block_names_ = {
      "131_A_129_B",
      "129_A",
      "131_BC",
      "133",
      "175_A_173",
      "177_A_175_B",
      "177_B",
      "AA",
      "AB",
      "AC",
      "AD",
      "AL",
      "AM",
      "AO",
      "AJ",
      "AK",
      "AP",
      "AV",
      "AF",
      "AG",
      "AE",
      "BP",
      "AQ_AS",
      "AX_AY_AZ",
      "BA",
      "BB",
      "BC",
      "BD",
      "BE",
      "BH",
      "BN",
      "BJ",
      "BM",
      "BL",
      "BQ",
      "BV_BT_BR",
      "CA",
      "UF",
      "UH",
      "UJ",
      "UK",
      "UL"
    };

    for(const QString& block : block_names_) {
        blocks_[block] = new TrackCircuit(block, parent, ":/svgs/svgs/Block_"+block+".svg");
    }

    return blocks_;
}
